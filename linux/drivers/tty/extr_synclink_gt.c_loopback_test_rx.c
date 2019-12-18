#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct slgt_info {unsigned char* tmp_rbuf; int /*<<< orphan*/  tmp_rbuf_count; TYPE_1__* rbufs; } ;
struct TYPE_3__ {unsigned char* buf; } ;

/* Variables and functions */
 unsigned char BIT8 ; 
 unsigned char BIT9 ; 
 int /*<<< orphan*/  DBGDATA (struct slgt_info*,unsigned char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ desc_complete (TYPE_1__) ; 
 int desc_count (TYPE_1__) ; 

__attribute__((used)) static int loopback_test_rx(struct slgt_info *info)
{
	unsigned char *src, *dest;
	int count;

	if (desc_complete(info->rbufs[0])) {
		count = desc_count(info->rbufs[0]);
		src   = info->rbufs[0].buf;
		dest  = info->tmp_rbuf;

		for( ; count ; count-=2, src+=2) {
			/* src=data byte (src+1)=status byte */
			if (!(*(src+1) & (BIT9 + BIT8))) {
				*dest = *src;
				dest++;
				info->tmp_rbuf_count++;
			}
		}
		DBGDATA(info, info->tmp_rbuf, info->tmp_rbuf_count, "rx");
		return 1;
	}
	return 0;
}