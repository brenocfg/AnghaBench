#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int s64 ;
struct TYPE_4__ {int /*<<< orphan*/  d32; } ;
struct TYPE_5__ {int position; int accum; TYPE_1__ part; } ;
typedef  TYPE_2__ emmh32_context ;

/* Variables and functions */
 int /*<<< orphan*/  MIC_ACCUM (int) ; 
 int* mask32 ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emmh32_final(emmh32_context *context, u8 digest[4])
{
	int	coeff_position, byte_position;
	u32	val;
  
	u64 sum, utmp;
	s64 stmp;

	coeff_position = context->position >> 2;
  
	/* deal with partial 32-bit word left over from last update */
	byte_position = context->position & 3;
	if (byte_position) {
		/* have a partial word in part to deal with */
		val = ntohl(context->part.d32);
		MIC_ACCUM(val & mask32[byte_position]);	/* zero empty bytes */
	}

	/* reduce the accumulated u64 to a 32-bit MIC */
	sum = context->accum;
	stmp = (sum  & 0xffffffffLL) - ((sum >> 32)  * 15);
	utmp = (stmp & 0xffffffffLL) - ((stmp >> 32) * 15);
	sum = utmp & 0xffffffffLL;
	if (utmp > 0x10000000fLL)
		sum -= 15;

	val = (u32)sum;
	digest[0] = (val>>24) & 0xFF;
	digest[1] = (val>>16) & 0xFF;
	digest[2] = (val>>8) & 0xFF;
	digest[3] = val & 0xFF;
}