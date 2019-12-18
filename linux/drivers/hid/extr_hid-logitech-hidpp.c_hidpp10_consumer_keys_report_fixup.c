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
typedef  int /*<<< orphan*/  u8 ;
struct hidpp_device {int dummy; } ;

/* Variables and functions */
 char* strnstr (char*,char const*,unsigned int) ; 

__attribute__((used)) static u8 *hidpp10_consumer_keys_report_fixup(struct hidpp_device *hidpp,
					      u8 *_rdesc, unsigned int *rsize)
{
	/* Note 0 terminated so we can use strnstr to search for this. */
	static const char consumer_rdesc_start[] = {
		0x05, 0x0C,	/* USAGE_PAGE (Consumer Devices)       */
		0x09, 0x01,	/* USAGE (Consumer Control)            */
		0xA1, 0x01,	/* COLLECTION (Application)            */
		0x85, 0x03,	/* REPORT_ID = 3                       */
		0x75, 0x10,	/* REPORT_SIZE (16)                    */
		0x95, 0x02,	/* REPORT_COUNT (2)                    */
		0x15, 0x01,	/* LOGICAL_MIN (1)                     */
		0x26, 0x00	/* LOGICAL_MAX (...                    */
	};
	char *consumer_rdesc, *rdesc = (char *)_rdesc;
	unsigned int size;

	consumer_rdesc = strnstr(rdesc, consumer_rdesc_start, *rsize);
	size = *rsize - (consumer_rdesc - rdesc);
	if (consumer_rdesc && size >= 25) {
		consumer_rdesc[15] = 0x7f;
		consumer_rdesc[16] = 0x10;
		consumer_rdesc[20] = 0x7f;
		consumer_rdesc[21] = 0x10;
	}
	return _rdesc;
}