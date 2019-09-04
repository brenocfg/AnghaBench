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
struct filter_tlv {int length; int /*<<< orphan*/  val; int /*<<< orphan*/  type; } ;
struct filter_action {int dummy; } ;
struct filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLSF_TLV_ACTION ; 
 int /*<<< orphan*/  CLSF_TLV_FILTER ; 

__attribute__((used)) static void fill_tlv(struct filter_tlv *tlv, struct filter *filter,
		struct filter_action *action)
{
	tlv->type = CLSF_TLV_FILTER;
	tlv->length = sizeof(struct filter);
	*((struct filter *)&tlv->val) = *filter;

	tlv = (struct filter_tlv *)((char *)tlv + sizeof(struct filter_tlv) +
			sizeof(struct filter));
	tlv->type = CLSF_TLV_ACTION;
	tlv->length = sizeof(struct filter_action);
	*((struct filter_action *)&tlv->val) = *action;
}