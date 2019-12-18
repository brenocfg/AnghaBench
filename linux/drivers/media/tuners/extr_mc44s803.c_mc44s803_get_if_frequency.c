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
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC44S803_IF2 ; 

__attribute__((used)) static int mc44s803_get_if_frequency(struct dvb_frontend *fe, u32 *frequency)
{
	*frequency = MC44S803_IF2; /* 36.125 MHz */
	return 0;
}