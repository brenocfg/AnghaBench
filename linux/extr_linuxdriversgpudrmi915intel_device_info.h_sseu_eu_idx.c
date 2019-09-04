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
struct sseu_dev_info {int max_subslices; int /*<<< orphan*/  max_eus_per_subslice; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_BYTE ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sseu_eu_idx(const struct sseu_dev_info *sseu,
			      int slice, int subslice)
{
	int subslice_stride = DIV_ROUND_UP(sseu->max_eus_per_subslice,
					   BITS_PER_BYTE);
	int slice_stride = sseu->max_subslices * subslice_stride;

	return slice * slice_stride + subslice * subslice_stride;
}