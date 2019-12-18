#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct vsc73xx_counter {char* name; } ;
struct vsc73xx {int dummy; } ;
struct dsa_switch {struct vsc73xx* priv; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_STATS ; 
 int /*<<< orphan*/  VSC73XX_BLOCK_MAC ; 
 int /*<<< orphan*/  VSC73XX_C_CFG ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,char*,int) ; 
 struct vsc73xx_counter* vsc73xx_find_counter (struct vsc73xx*,scalar_t__,int) ; 
 int vsc73xx_read (struct vsc73xx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void vsc73xx_get_strings(struct dsa_switch *ds, int port, u32 stringset,
				uint8_t *data)
{
	const struct vsc73xx_counter *cnt;
	struct vsc73xx *vsc = ds->priv;
	u8 indices[6];
	int i, j;
	u32 val;
	int ret;

	if (stringset != ETH_SS_STATS)
		return;

	ret = vsc73xx_read(vsc, VSC73XX_BLOCK_MAC, port,
			   VSC73XX_C_CFG, &val);
	if (ret)
		return;

	indices[0] = (val & 0x1f); /* RX counter 0 */
	indices[1] = ((val >> 5) & 0x1f); /* RX counter 1 */
	indices[2] = ((val >> 10) & 0x1f); /* RX counter 2 */
	indices[3] = ((val >> 16) & 0x1f); /* TX counter 0 */
	indices[4] = ((val >> 21) & 0x1f); /* TX counter 1 */
	indices[5] = ((val >> 26) & 0x1f); /* TX counter 2 */

	/* The first counters is the RX octets */
	j = 0;
	strncpy(data + j * ETH_GSTRING_LEN,
		"RxEtherStatsOctets", ETH_GSTRING_LEN);
	j++;

	/* Each port supports recording 3 RX counters and 3 TX counters,
	 * figure out what counters we use in this set-up and return the
	 * names of them. The hardware default counters will be number of
	 * packets on RX/TX, combined broadcast+multicast packets RX/TX and
	 * total error packets RX/TX.
	 */
	for (i = 0; i < 3; i++) {
		cnt = vsc73xx_find_counter(vsc, indices[i], false);
		if (cnt)
			strncpy(data + j * ETH_GSTRING_LEN,
				cnt->name, ETH_GSTRING_LEN);
		j++;
	}

	/* TX stats begins with the number of TX octets */
	strncpy(data + j * ETH_GSTRING_LEN,
		"TxEtherStatsOctets", ETH_GSTRING_LEN);
	j++;

	for (i = 3; i < 6; i++) {
		cnt = vsc73xx_find_counter(vsc, indices[i], true);
		if (cnt)
			strncpy(data + j * ETH_GSTRING_LEN,
				cnt->name, ETH_GSTRING_LEN);
		j++;
	}
}