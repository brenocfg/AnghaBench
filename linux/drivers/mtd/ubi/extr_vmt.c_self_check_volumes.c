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
struct ubi_device {int vtbl_slots; } ;

/* Variables and functions */
 int self_check_volume (struct ubi_device*,int) ; 
 int /*<<< orphan*/  ubi_dbg_chk_gen (struct ubi_device*) ; 

__attribute__((used)) static int self_check_volumes(struct ubi_device *ubi)
{
	int i, err = 0;

	if (!ubi_dbg_chk_gen(ubi))
		return 0;

	for (i = 0; i < ubi->vtbl_slots; i++) {
		err = self_check_volume(ubi, i);
		if (err)
			break;
	}

	return err;
}