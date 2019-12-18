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
struct intel_gvt_gtt_entry {int /*<<< orphan*/  val64; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTT_SPTE_FLAG_64K_SPLITED ; 

__attribute__((used)) static void gen8_gtt_clear_64k_splited(struct intel_gvt_gtt_entry *e)
{
	e->val64 &= ~GTT_SPTE_FLAG_64K_SPLITED;
}