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
typedef  int u32 ;
struct input_dev {int dummy; } ;
struct cros_ec_keyb {struct input_dev* bs_idev; } ;
struct cros_ec_bs_map {unsigned int ev_type; int inverted; int /*<<< orphan*/  bit; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cros_ec_bs_map*) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 struct cros_ec_bs_map* cros_ec_keyb_bs ; 
 int /*<<< orphan*/  input_event (struct input_dev*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void cros_ec_keyb_report_bs(struct cros_ec_keyb *ckdev,
				   unsigned int ev_type, u32 mask)

{
	struct input_dev *idev = ckdev->bs_idev;
	int i;

	for (i = 0; i < ARRAY_SIZE(cros_ec_keyb_bs); i++) {
		const struct cros_ec_bs_map *map = &cros_ec_keyb_bs[i];

		if (map->ev_type != ev_type)
			continue;

		input_event(idev, ev_type, map->code,
			    !!(mask & BIT(map->bit)) ^ map->inverted);
	}
	input_sync(idev);
}