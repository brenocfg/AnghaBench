#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_frontend {TYPE_1__* dvb; } ;
struct av7110 {int dummy; } ;
typedef  enum fe_sec_mini_cmd { ____Placeholder_fe_sec_mini_cmd } fe_sec_mini_cmd ;
struct TYPE_2__ {struct av7110* priv; } ;

/* Variables and functions */
 int av7110_diseqc_send (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int av7110_diseqc_send_burst(struct dvb_frontend* fe,
				    enum fe_sec_mini_cmd minicmd)
{
	struct av7110* av7110 = fe->dvb->priv;

	return av7110_diseqc_send(av7110, 0, NULL, minicmd);
}