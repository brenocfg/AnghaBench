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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 scalar_t__ MXL_RegRead (struct dvb_frontend*,int,int*) ; 

__attribute__((used)) static u16 MXL_GetCHRegister(struct dvb_frontend *fe, u8 *RegNum, u8 *RegVal,
	int *count)
{
	u16 status = 0;
	int i ;

/* add 77, 166, 167, 168 register for 2.6.12 */
#ifdef _MXL_PRODUCTION
	static const u8 RegAddr[] = {
		14, 15, 16, 17, 22, 43, 65, 68, 69, 70, 73, 92, 93, 106,
		107, 108, 109, 110, 111, 112, 136, 138, 149, 77, 166, 167, 168
	};
#else
	static const u8 RegAddr[] = {
		14, 15, 16, 17, 22, 43, 68, 69, 70, 73, 92, 93, 106,
		107, 108, 109, 110, 111, 112, 136, 138, 149, 77, 166, 167, 168
	};
	/*
	u8 RegAddr[171];
	for (i = 0; i <= 170; i++)
		RegAddr[i] = i;
	*/
#endif

	*count = ARRAY_SIZE(RegAddr);

	for (i = 0 ; i < *count; i++) {
		RegNum[i] = RegAddr[i];
		status += MXL_RegRead(fe, RegNum[i], &RegVal[i]);
	}

	return status;
}