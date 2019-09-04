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
struct TYPE_3__ {int decodelen; int nbytes; int* decodebuf; int key; } ;
typedef  TYPE_1__ isdn_v110_stream ;

/* Variables and functions */

__attribute__((used)) static int
ValidHeaderBytes(isdn_v110_stream *v)
{
	int i;
	for (i = 0; (i < v->decodelen) && (i < v->nbytes); i++)
		if ((v->decodebuf[i] & v->key) != 0)
			break;
	return i;
}