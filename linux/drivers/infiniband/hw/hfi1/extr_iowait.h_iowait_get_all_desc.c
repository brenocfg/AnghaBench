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
typedef  scalar_t__ u32 ;
struct iowait {int /*<<< orphan*/ * wait; } ;

/* Variables and functions */
 size_t IOWAIT_IB_SE ; 
 size_t IOWAIT_TID_SE ; 
 scalar_t__ iowait_get_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 iowait_get_all_desc(struct iowait *w)
{
	u32 num_desc = 0;

	num_desc = iowait_get_desc(&w->wait[IOWAIT_IB_SE]);
	num_desc += iowait_get_desc(&w->wait[IOWAIT_TID_SE]);
	return num_desc;
}