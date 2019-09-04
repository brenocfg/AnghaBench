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
struct rtattr {int dummy; } ;
struct crypto_template {int dummy; } ;
struct crypto_attr_type {int type; int mask; } ;

/* Variables and functions */
#define  CRYPTO_ALG_TYPE_DIGEST 128 
 int CRYPTO_ALG_TYPE_MASK ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct crypto_attr_type*) ; 
 int PTR_ERR (struct crypto_attr_type*) ; 
 struct crypto_attr_type* crypto_get_attr_type (struct rtattr**) ; 
 int mcryptd_create_hash (struct crypto_template*,struct rtattr**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mqueue ; 

__attribute__((used)) static int mcryptd_create(struct crypto_template *tmpl, struct rtattr **tb)
{
	struct crypto_attr_type *algt;

	algt = crypto_get_attr_type(tb);
	if (IS_ERR(algt))
		return PTR_ERR(algt);

	switch (algt->type & algt->mask & CRYPTO_ALG_TYPE_MASK) {
	case CRYPTO_ALG_TYPE_DIGEST:
		return mcryptd_create_hash(tmpl, tb, &mqueue);
	break;
	}

	return -EINVAL;
}