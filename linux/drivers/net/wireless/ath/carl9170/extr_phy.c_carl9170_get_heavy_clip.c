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
struct ar9170_calctl_edges {int channel; int power_flags; } ;
struct ar9170 {int dummy; } ;
typedef  enum carl9170_bw { ____Placeholder_carl9170_bw } carl9170_bw ;

/* Variables and functions */
 int AR5416_NUM_BAND_EDGES ; 
 int AR9170_CALCTL_EDGE_FLAGS ; 
 int CARL9170_BW_40_ABOVE ; 
 int CARL9170_BW_40_BELOW ; 

__attribute__((used)) static u8 carl9170_get_heavy_clip(struct ar9170 *ar, u32 freq,
	enum carl9170_bw bw, struct ar9170_calctl_edges edges[])
{
	u8 f;
	int i;
	u8 rc = 0;

	if (freq < 3000)
		f = freq - 2300;
	else
		f = (freq - 4800) / 5;

	if (bw == CARL9170_BW_40_BELOW || bw == CARL9170_BW_40_ABOVE)
		rc |= 0xf0;

	for (i = 0; i < AR5416_NUM_BAND_EDGES; i++) {
		if (edges[i].channel == 0xff)
			break;
		if (f == edges[i].channel) {
			if (!(edges[i].power_flags & AR9170_CALCTL_EDGE_FLAGS))
				rc |= 0x0f;
			break;
		}
	}

	return rc;
}