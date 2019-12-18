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
struct dvb_usb_device {int dummy; } ;
struct cxusb_medion_auxbuf {int dummy; } ;
struct cxusb_bt656_params {scalar_t__ fmode; scalar_t__ line; int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 scalar_t__ LINE_SAMPLES ; 
 scalar_t__ START_SEARCH ; 
 int /*<<< orphan*/  cxusb_medion_cs_line_smpl (struct cxusb_bt656_params*,unsigned int,unsigned char) ; 
 int cxusb_medion_cs_start_sch (struct dvb_usb_device*,struct cxusb_medion_auxbuf*,struct cxusb_bt656_params*,unsigned int) ; 

__attribute__((used)) static bool cxusb_medion_copy_samples(struct dvb_usb_device *dvbdev,
				      struct cxusb_medion_auxbuf *auxbuf,
				      struct cxusb_bt656_params *bt656,
				      unsigned int maxlinesamples,
				      unsigned char val)
{
	if (bt656->fmode == START_SEARCH && bt656->line > 0)
		return cxusb_medion_cs_start_sch(dvbdev, auxbuf, bt656,
						 maxlinesamples);
	else if (bt656->fmode == LINE_SAMPLES)
		cxusb_medion_cs_line_smpl(bt656, maxlinesamples, val);
	else /* TODO: copy VBI samples */
		bt656->pos++;

	return true;
}