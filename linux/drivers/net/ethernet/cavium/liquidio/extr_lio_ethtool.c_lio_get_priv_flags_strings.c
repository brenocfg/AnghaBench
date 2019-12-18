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
typedef  int /*<<< orphan*/  u8 ;
struct octeon_device {int chip_id; } ;
struct lio {int /*<<< orphan*/  netdev; struct octeon_device* oct_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
#define  OCTEON_CN23XX_PF_VID 131 
#define  OCTEON_CN23XX_VF_VID 130 
#define  OCTEON_CN66XX 129 
#define  OCTEON_CN68XX 128 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_info (struct lio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char** oct_priv_flags_strings ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void lio_get_priv_flags_strings(struct lio *lio, u8 *data)
{
	struct octeon_device *oct_dev = lio->oct_dev;
	int i;

	switch (oct_dev->chip_id) {
	case OCTEON_CN23XX_PF_VID:
	case OCTEON_CN23XX_VF_VID:
		for (i = 0; i < ARRAY_SIZE(oct_priv_flags_strings); i++) {
			sprintf(data, "%s", oct_priv_flags_strings[i]);
			data += ETH_GSTRING_LEN;
		}
		break;
	case OCTEON_CN68XX:
	case OCTEON_CN66XX:
		break;
	default:
		netif_info(lio, drv, lio->netdev, "Unknown Chip !!\n");
		break;
	}
}