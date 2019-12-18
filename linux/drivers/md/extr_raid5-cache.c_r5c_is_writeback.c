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
struct r5l_log {scalar_t__ r5c_journal_mode; } ;

/* Variables and functions */
 scalar_t__ R5C_JOURNAL_MODE_WRITE_BACK ; 

bool r5c_is_writeback(struct r5l_log *log)
{
	return (log != NULL &&
		log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_BACK);
}