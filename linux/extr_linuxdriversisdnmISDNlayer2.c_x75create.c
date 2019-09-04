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
struct layer2 {int /*<<< orphan*/  ch; } ;
struct channel_req {scalar_t__ protocol; int /*<<< orphan*/ * ch; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 scalar_t__ ISDN_P_B_HDLC ; 
 scalar_t__ ISDN_P_B_X75SLP ; 
 struct layer2* create_l2 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
x75create(struct channel_req *crq)
{
	struct layer2	*l2;

	if (crq->protocol != ISDN_P_B_X75SLP)
		return -EPROTONOSUPPORT;
	l2 = create_l2(crq->ch, crq->protocol, 0, 0, 0);
	if (!l2)
		return -ENOMEM;
	crq->ch = &l2->ch;
	crq->protocol = ISDN_P_B_HDLC;
	return 0;
}