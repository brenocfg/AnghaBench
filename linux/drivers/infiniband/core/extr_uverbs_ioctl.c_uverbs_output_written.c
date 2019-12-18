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
struct uverbs_attr_bundle {int dummy; } ;
struct uverbs_attr {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct uverbs_attr const*) ; 
 int PTR_ERR (struct uverbs_attr const*) ; 
 struct uverbs_attr* uverbs_attr_get (struct uverbs_attr_bundle const*,size_t) ; 
 int uverbs_set_output (struct uverbs_attr_bundle const*,struct uverbs_attr const*) ; 

int uverbs_output_written(const struct uverbs_attr_bundle *bundle, size_t idx)
{
	const struct uverbs_attr *attr = uverbs_attr_get(bundle, idx);

	if (IS_ERR(attr))
		return PTR_ERR(attr);

	return uverbs_set_output(bundle, attr);
}