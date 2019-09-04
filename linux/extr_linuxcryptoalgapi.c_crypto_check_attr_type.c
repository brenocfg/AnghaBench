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
typedef  int u32 ;
struct rtattr {int dummy; } ;
struct crypto_attr_type {int type; int mask; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct crypto_attr_type*) ; 
 int PTR_ERR (struct crypto_attr_type*) ; 
 struct crypto_attr_type* crypto_get_attr_type (struct rtattr**) ; 

int crypto_check_attr_type(struct rtattr **tb, u32 type)
{
	struct crypto_attr_type *algt;

	algt = crypto_get_attr_type(tb);
	if (IS_ERR(algt))
		return PTR_ERR(algt);

	if ((algt->type ^ type) & algt->mask)
		return -EINVAL;

	return 0;
}