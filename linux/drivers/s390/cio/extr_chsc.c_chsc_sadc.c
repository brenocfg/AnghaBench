#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct subchannel_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  code; } ;
struct TYPE_4__ {int length; int code; } ;
struct chsc_scssc_area {int ks; int kc; int word_with_d_bit; TYPE_2__ response; struct subchannel_id schid; int /*<<< orphan*/  isc; void* subchannel_indicator_addr; void* summary_indicator_addr; scalar_t__ operation_code; TYPE_1__ request; } ;
struct TYPE_6__ {scalar_t__ aif_tdd; } ;

/* Variables and functions */
 int EIO ; 
 int PAGE_DEFAULT_KEY ; 
 int /*<<< orphan*/  QDIO_AIRQ_ISC ; 
 scalar_t__ chsc (struct chsc_scssc_area*) ; 
 int chsc_error_from_response (int /*<<< orphan*/ ) ; 
 TYPE_3__ css_general_characteristics ; 
 int /*<<< orphan*/  memset (struct chsc_scssc_area*,int /*<<< orphan*/ ,int) ; 

int chsc_sadc(struct subchannel_id schid, struct chsc_scssc_area *scssc,
	      u64 summary_indicator_addr, u64 subchannel_indicator_addr)
{
	memset(scssc, 0, sizeof(*scssc));
	scssc->request.length = 0x0fe0;
	scssc->request.code = 0x0021;
	scssc->operation_code = 0;

	scssc->summary_indicator_addr = summary_indicator_addr;
	scssc->subchannel_indicator_addr = subchannel_indicator_addr;

	scssc->ks = PAGE_DEFAULT_KEY >> 4;
	scssc->kc = PAGE_DEFAULT_KEY >> 4;
	scssc->isc = QDIO_AIRQ_ISC;
	scssc->schid = schid;

	/* enable the time delay disablement facility */
	if (css_general_characteristics.aif_tdd)
		scssc->word_with_d_bit = 0x10000000;

	if (chsc(scssc))
		return -EIO;

	return chsc_error_from_response(scssc->response.code);
}