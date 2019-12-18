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
struct link_init_data {int dummy; } ;
struct dc_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int construct (struct dc_link*,struct link_init_data const*) ; 
 int /*<<< orphan*/  kfree (struct dc_link*) ; 
 struct dc_link* kzalloc (int,int /*<<< orphan*/ ) ; 

struct dc_link *link_create(const struct link_init_data *init_params)
{
	struct dc_link *link =
			kzalloc(sizeof(*link), GFP_KERNEL);

	if (NULL == link)
		goto alloc_fail;

	if (false == construct(link, init_params))
		goto construct_fail;

	return link;

construct_fail:
	kfree(link);

alloc_fail:
	return NULL;
}