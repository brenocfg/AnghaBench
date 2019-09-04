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
struct cxl_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cxl_context* kzalloc (int,int /*<<< orphan*/ ) ; 

struct cxl_context *cxl_context_alloc(void)
{
	return kzalloc(sizeof(struct cxl_context), GFP_KERNEL);
}