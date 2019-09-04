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
typedef  size_t byte ;
struct TYPE_3__ {int* info; scalar_t__ length; } ;
typedef  TYPE_1__ API_PARSE ;

/* Variables and functions */
 int CHI ; 
 int ESC ; 

__attribute__((used)) static byte getChannel(API_PARSE *p)
{
	byte i;

	if (p) {
		for (i = 2; i < (byte)p->length; i += p->info[i] + 2) {
			if (p->info[i] == 2) {
				if (p->info[i - 1] == ESC && p->info[i + 1] == CHI) return (p->info[i + 2]);
			}
		}
	}
	return 0;
}