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
struct ltq_mfp_pin {unsigned int* func; } ;

/* Variables and functions */
 int EINVAL ; 
 int LTQ_MAX_MUX ; 

__attribute__((used)) static int match_mux(const struct ltq_mfp_pin *mfp, unsigned mux)
{
	int i;
	for (i = 0; i < LTQ_MAX_MUX; i++) {
		if (mfp->func[i] == mux)
			break;
	}
	if (i >= LTQ_MAX_MUX)
		return -EINVAL;
	return i;
}