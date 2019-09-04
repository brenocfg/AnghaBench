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
typedef  int /*<<< orphan*/  u32 ;
struct rsxx_cardinfo {int dummy; } ;

/* Variables and functions */
 int issue_creg_rw (struct rsxx_cardinfo*,int /*<<< orphan*/ ,unsigned int,void*,int,int) ; 

int rsxx_creg_read(struct rsxx_cardinfo *card,
		       u32 addr,
		       unsigned int size8,
		       void *data,
		       int byte_stream)
{
	return issue_creg_rw(card, addr, size8, data, byte_stream, 1);
}