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
typedef  scalar_t__ u32 ;
struct sis_video_info {scalar_t__ sisfb_id; int /*<<< orphan*/  sisfb_heap; scalar_t__ havenoheap; } ;
struct SIS_OH {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,unsigned int) ; 
 scalar_t__ SISFB_ID ; 
 struct SIS_OH* sisfb_poh_free (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
sis_int_free(struct sis_video_info *ivideo, u32 base)
{
	struct SIS_OH *poh;

	if((!ivideo) || (ivideo->sisfb_id != SISFB_ID) || (ivideo->havenoheap))
		return;

	poh = sisfb_poh_free(&ivideo->sisfb_heap, base);

	if(poh == NULL) {
		DPRINTK("sisfb: sisfb_poh_free() failed at base 0x%x\n",
			(unsigned int) base);
	}
}