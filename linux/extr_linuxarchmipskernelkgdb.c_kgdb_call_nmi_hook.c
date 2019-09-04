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
typedef  int /*<<< orphan*/  mm_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_ds () ; 
 int /*<<< orphan*/  get_fs () ; 
 int /*<<< orphan*/  kgdb_nmicallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kgdb_call_nmi_hook(void *ignored)
{
	mm_segment_t old_fs;

	old_fs = get_fs();
	set_fs(get_ds());

	kgdb_nmicallback(raw_smp_processor_id(), NULL);

	set_fs(old_fs);
}