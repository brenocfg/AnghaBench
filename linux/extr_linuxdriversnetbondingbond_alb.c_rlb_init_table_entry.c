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
struct rlb_client_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct rlb_client_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rlb_init_table_entry_dst (struct rlb_client_info*) ; 
 int /*<<< orphan*/  rlb_init_table_entry_src (struct rlb_client_info*) ; 

__attribute__((used)) static void rlb_init_table_entry(struct rlb_client_info *entry)
{
	memset(entry, 0, sizeof(struct rlb_client_info));
	rlb_init_table_entry_dst(entry);
	rlb_init_table_entry_src(entry);
}