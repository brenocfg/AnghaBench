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
struct isowbuf_t {int read; int write; } ;

/* Variables and functions */
 int BAS_OUTBUFPAD ; 
 int BAS_OUTBUFSIZE ; 

__attribute__((used)) static inline int isowbuf_freebytes(struct isowbuf_t *iwb)
{
	int read, write, freebytes;

	read = iwb->read;
	write = iwb->write;
	freebytes = read - write;
	if (freebytes > 0) {
		/* no wraparound: need padding space within regular area */
		return freebytes - BAS_OUTBUFPAD;
	} else if (read < BAS_OUTBUFPAD) {
		/* wraparound: can use space up to end of regular area */
		return BAS_OUTBUFSIZE - write;
	} else {
		/* following the wraparound yields more space */
		return freebytes + BAS_OUTBUFSIZE - BAS_OUTBUFPAD;
	}
}