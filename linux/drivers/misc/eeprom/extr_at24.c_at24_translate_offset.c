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
struct at24_data {int flags; struct at24_client* client; } ;
struct at24_client {int dummy; } ;

/* Variables and functions */
 int AT24_FLAG_ADDR16 ; 

__attribute__((used)) static struct at24_client *at24_translate_offset(struct at24_data *at24,
						 unsigned int *offset)
{
	unsigned int i;

	if (at24->flags & AT24_FLAG_ADDR16) {
		i = *offset >> 16;
		*offset &= 0xffff;
	} else {
		i = *offset >> 8;
		*offset &= 0xff;
	}

	return &at24->client[i];
}