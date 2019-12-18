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
struct qeth_ipa_info {int supported_funcs; } ;
typedef  enum qeth_ipa_setadp_cmd { ____Placeholder_qeth_ipa_setadp_cmd } qeth_ipa_setadp_cmd ;

/* Variables and functions */

__attribute__((used)) static inline int qeth_is_adp_supported(struct qeth_ipa_info *ipa,
		enum qeth_ipa_setadp_cmd func)
{
	return (ipa->supported_funcs & func);
}