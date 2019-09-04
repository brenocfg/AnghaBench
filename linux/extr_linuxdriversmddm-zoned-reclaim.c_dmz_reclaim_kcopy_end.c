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
struct dmz_reclaim {int /*<<< orphan*/  flags; int /*<<< orphan*/  kc_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_RECLAIM_KCOPY ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmz_reclaim_kcopy_end(int read_err, unsigned long write_err,
				  void *context)
{
	struct dmz_reclaim *zrc = context;

	if (read_err || write_err)
		zrc->kc_err = -EIO;
	else
		zrc->kc_err = 0;

	clear_bit_unlock(DMZ_RECLAIM_KCOPY, &zrc->flags);
	smp_mb__after_atomic();
	wake_up_bit(&zrc->flags, DMZ_RECLAIM_KCOPY);
}