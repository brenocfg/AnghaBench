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
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t MACSEC_ATTR_SA_CONFIG ; 
 int /*<<< orphan*/  MACSEC_SA_ATTR_MAX ; 
 int /*<<< orphan*/  macsec_genl_sa_policy ; 
 scalar_t__ nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_sa_config(struct nlattr **attrs, struct nlattr **tb_sa)
{
	if (!attrs[MACSEC_ATTR_SA_CONFIG])
		return -EINVAL;

	if (nla_parse_nested_deprecated(tb_sa, MACSEC_SA_ATTR_MAX, attrs[MACSEC_ATTR_SA_CONFIG], macsec_genl_sa_policy, NULL))
		return -EINVAL;

	return 0;
}