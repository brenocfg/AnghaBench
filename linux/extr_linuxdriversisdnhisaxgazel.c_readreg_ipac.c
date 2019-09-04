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
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  bytein (unsigned int) ; 
 int /*<<< orphan*/  byteout (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u_char
readreg_ipac(unsigned int adr, u_short off)
{
	register u_char ret;

	byteout(adr, off);
	ret = bytein(adr + 4);
	return ret;
}