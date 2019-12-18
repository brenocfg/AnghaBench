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
typedef  int u8 ;
typedef  struct zd_ioreq32 {int value; } const zd_ioreq32 ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq32 const*) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_iowrite32a_locked (struct zd_chip*,struct zd_ioreq32 const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zd_write_mac_addr_common(struct zd_chip *chip, const u8 *mac_addr,
				    const struct zd_ioreq32 *in_reqs,
				    const char *type)
{
	int r;
	struct zd_ioreq32 reqs[2] = {in_reqs[0], in_reqs[1]};

	if (mac_addr) {
		reqs[0].value = (mac_addr[3] << 24)
			      | (mac_addr[2] << 16)
			      | (mac_addr[1] <<  8)
			      |  mac_addr[0];
		reqs[1].value = (mac_addr[5] <<  8)
			      |  mac_addr[4];
		dev_dbg_f(zd_chip_dev(chip), "%s addr %pM\n", type, mac_addr);
	} else {
		dev_dbg_f(zd_chip_dev(chip), "set NULL %s\n", type);
	}

	mutex_lock(&chip->mutex);
	r = zd_iowrite32a_locked(chip, reqs, ARRAY_SIZE(reqs));
	mutex_unlock(&chip->mutex);
	return r;
}