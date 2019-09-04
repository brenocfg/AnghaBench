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
struct dc_gamma {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct dc_gamma* kvzalloc (int,int /*<<< orphan*/ ) ; 

struct dc_gamma *dc_create_gamma(void)
{
	struct dc_gamma *gamma = kvzalloc(sizeof(*gamma), GFP_KERNEL);

	if (gamma == NULL)
		goto alloc_fail;

	kref_init(&gamma->refcount);
	return gamma;

alloc_fail:
	return NULL;
}