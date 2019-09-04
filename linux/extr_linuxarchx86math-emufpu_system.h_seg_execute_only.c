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
struct desc_struct {int type; } ;

/* Variables and functions */
 int SEG_TYPE_EXECUTE ; 
 int SEG_TYPE_EXECUTE_MASK ; 

__attribute__((used)) static inline bool seg_execute_only(struct desc_struct *d)
{
	return (d->type & SEG_TYPE_EXECUTE_MASK) == SEG_TYPE_EXECUTE;
}