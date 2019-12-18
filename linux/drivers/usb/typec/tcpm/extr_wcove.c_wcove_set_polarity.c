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
struct wcove_typec {int dummy; } ;
struct tcpc_dev {int dummy; } ;
typedef  enum typec_cc_polarity { ____Placeholder_typec_cc_polarity } typec_cc_polarity ;

/* Variables and functions */
 int /*<<< orphan*/  WCOVE_FUNC_ORIENTATION ; 
 struct wcove_typec* tcpc_to_wcove (struct tcpc_dev*) ; 
 int wcove_typec_func (struct wcove_typec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wcove_set_polarity(struct tcpc_dev *tcpc, enum typec_cc_polarity pol)
{
	struct wcove_typec *wcove = tcpc_to_wcove(tcpc);

	return wcove_typec_func(wcove, WCOVE_FUNC_ORIENTATION, pol);
}