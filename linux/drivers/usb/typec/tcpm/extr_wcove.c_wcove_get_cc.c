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
struct wcove_typec {int /*<<< orphan*/  regmap; } ;
struct tcpc_dev {int dummy; } ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;

/* Variables and functions */
 int /*<<< orphan*/  USBC_CC1_STATUS ; 
 int /*<<< orphan*/  USBC_CC2_STATUS ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct wcove_typec* tcpc_to_wcove (struct tcpc_dev*) ; 
 int wcove_to_typec_cc (unsigned int) ; 

__attribute__((used)) static int wcove_get_cc(struct tcpc_dev *tcpc, enum typec_cc_status *cc1,
			enum typec_cc_status *cc2)
{
	struct wcove_typec *wcove = tcpc_to_wcove(tcpc);
	unsigned int cc1_status;
	unsigned int cc2_status;
	int ret;

	ret = regmap_read(wcove->regmap, USBC_CC1_STATUS, &cc1_status);
	if (ret)
		return ret;

	ret = regmap_read(wcove->regmap, USBC_CC2_STATUS, &cc2_status);
	if (ret)
		return ret;

	*cc1 = wcove_to_typec_cc(cc1_status);
	*cc2 = wcove_to_typec_cc(cc2_status);

	return 0;
}