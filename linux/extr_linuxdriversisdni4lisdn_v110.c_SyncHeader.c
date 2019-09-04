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
struct TYPE_3__ {unsigned char* decodebuf; int decodelen; unsigned char key; } ;
typedef  TYPE_1__ isdn_v110_stream ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static void
SyncHeader(isdn_v110_stream *v)
{
	unsigned char *rbuf = v->decodebuf;
	int len = v->decodelen;

	if (len == 0)
		return;
	for (rbuf++, len--; len > 0; len--, rbuf++)	/* such den SyncHeader in buf ! */
		if ((*rbuf & v->key) == 0)	/* erstes byte gefunden ?       */
			break;  /* jupp!                        */
	if (len)
		memcpy(v->decodebuf, rbuf, len);

	v->decodelen = len;
#ifdef ISDN_V110_DEBUG
	printk(KERN_DEBUG "isdn_v110: Header resync\n");
#endif
}