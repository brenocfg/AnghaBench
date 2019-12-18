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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct qeth_card {int dummy; } ;
typedef  enum qeth_ipa_funcs { ____Placeholder_qeth_ipa_funcs } qeth_ipa_funcs ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_PROT_IPV4 ; 
 int qeth_send_simple_setassparms_prot (struct qeth_card*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qeth_send_simple_setassparms(struct qeth_card *card,
					       enum qeth_ipa_funcs ipa_func,
					       u16 cmd_code, u32 *data)
{
	return qeth_send_simple_setassparms_prot(card, ipa_func, cmd_code,
						 data, QETH_PROT_IPV4);
}