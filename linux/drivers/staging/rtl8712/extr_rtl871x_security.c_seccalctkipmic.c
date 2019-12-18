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
typedef  int u32 ;
struct mic_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8712_secgetmic (struct mic_data*,int*) ; 
 int /*<<< orphan*/  r8712_secmicappend (struct mic_data*,int*,int) ; 
 int /*<<< orphan*/  r8712_secmicsetkey (struct mic_data*,int*) ; 

void seccalctkipmic(u8 *key, u8 *header, u8 *data, u32 data_len, u8 *mic_code,
		    u8 pri)
{

	struct mic_data	micdata;
	u8 priority[4] = {0x0, 0x0, 0x0, 0x0};

	r8712_secmicsetkey(&micdata, key);
	priority[0] = pri;
	/* Michael MIC pseudo header: DA, SA, 3 x 0, Priority */
	if (header[1] & 1) {   /* ToDS==1 */
		r8712_secmicappend(&micdata, &header[16], 6);  /* DA */
		if (header[1] & 2)  /* From Ds==1 */
			r8712_secmicappend(&micdata, &header[24], 6);
		else
			r8712_secmicappend(&micdata, &header[10], 6);
	} else {	/* ToDS==0 */
		r8712_secmicappend(&micdata, &header[4], 6);   /* DA */
		if (header[1] & 2)  /* From Ds==1 */
			r8712_secmicappend(&micdata, &header[16], 6);
		else
			r8712_secmicappend(&micdata, &header[10], 6);
	}
	r8712_secmicappend(&micdata, &priority[0], 4);
	r8712_secmicappend(&micdata, data, data_len);
	r8712_secgetmic(&micdata, mic_code);
}