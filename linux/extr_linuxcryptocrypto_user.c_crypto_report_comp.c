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
struct sk_buff {int dummy; } ;
struct crypto_report_comp {int /*<<< orphan*/  type; } ;
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTOCFGA_REPORT_COMPRESS ; 
 int EMSGSIZE ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct crypto_report_comp*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int crypto_report_comp(struct sk_buff *skb, struct crypto_alg *alg)
{
	struct crypto_report_comp rcomp;

	strncpy(rcomp.type, "compression", sizeof(rcomp.type));
	if (nla_put(skb, CRYPTOCFGA_REPORT_COMPRESS,
		    sizeof(struct crypto_report_comp), &rcomp))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -EMSGSIZE;
}