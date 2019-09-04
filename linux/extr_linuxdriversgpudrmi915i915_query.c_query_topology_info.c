#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  topo ;
struct drm_i915_query_topology_info {scalar_t__ flags; int max_slices; int max_subslices; int max_eus_per_subslice; int subslice_offset; int subslice_stride; int eu_offset; int eu_stride; } ;
struct sseu_dev_info {int max_slices; int max_subslices; int max_eus_per_subslice; struct drm_i915_query_topology_info* eu_mask; struct drm_i915_query_topology_info* subslice_mask; struct drm_i915_query_topology_info slice_mask; } ;
struct drm_i915_query_item {scalar_t__ flags; int length; scalar_t__ data_ptr; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {struct sseu_dev_info sseu; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 TYPE_1__* INTEL_INFO (struct drm_i915_private*) ; 
 int /*<<< orphan*/  VERIFY_WRITE ; 
 scalar_t__ __copy_to_user (int /*<<< orphan*/ ,struct drm_i915_query_topology_info*,int) ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_from_user (struct drm_i915_query_topology_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct drm_i915_query_topology_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  u64_to_user_ptr (scalar_t__) ; 

__attribute__((used)) static int query_topology_info(struct drm_i915_private *dev_priv,
			       struct drm_i915_query_item *query_item)
{
	const struct sseu_dev_info *sseu = &INTEL_INFO(dev_priv)->sseu;
	struct drm_i915_query_topology_info topo;
	u32 slice_length, subslice_length, eu_length, total_length;

	if (query_item->flags != 0)
		return -EINVAL;

	if (sseu->max_slices == 0)
		return -ENODEV;

	BUILD_BUG_ON(sizeof(u8) != sizeof(sseu->slice_mask));

	slice_length = sizeof(sseu->slice_mask);
	subslice_length = sseu->max_slices *
		DIV_ROUND_UP(sseu->max_subslices,
			     sizeof(sseu->subslice_mask[0]) * BITS_PER_BYTE);
	eu_length = sseu->max_slices * sseu->max_subslices *
		DIV_ROUND_UP(sseu->max_eus_per_subslice, BITS_PER_BYTE);

	total_length = sizeof(topo) + slice_length + subslice_length + eu_length;

	if (query_item->length == 0)
		return total_length;

	if (query_item->length < total_length)
		return -EINVAL;

	if (copy_from_user(&topo, u64_to_user_ptr(query_item->data_ptr),
			   sizeof(topo)))
		return -EFAULT;

	if (topo.flags != 0)
		return -EINVAL;

	if (!access_ok(VERIFY_WRITE, u64_to_user_ptr(query_item->data_ptr),
		       total_length))
		return -EFAULT;

	memset(&topo, 0, sizeof(topo));
	topo.max_slices = sseu->max_slices;
	topo.max_subslices = sseu->max_subslices;
	topo.max_eus_per_subslice = sseu->max_eus_per_subslice;

	topo.subslice_offset = slice_length;
	topo.subslice_stride = DIV_ROUND_UP(sseu->max_subslices, BITS_PER_BYTE);
	topo.eu_offset = slice_length + subslice_length;
	topo.eu_stride =
		DIV_ROUND_UP(sseu->max_eus_per_subslice, BITS_PER_BYTE);

	if (__copy_to_user(u64_to_user_ptr(query_item->data_ptr),
			   &topo, sizeof(topo)))
		return -EFAULT;

	if (__copy_to_user(u64_to_user_ptr(query_item->data_ptr + sizeof(topo)),
			   &sseu->slice_mask, slice_length))
		return -EFAULT;

	if (__copy_to_user(u64_to_user_ptr(query_item->data_ptr +
					   sizeof(topo) + slice_length),
			   sseu->subslice_mask, subslice_length))
		return -EFAULT;

	if (__copy_to_user(u64_to_user_ptr(query_item->data_ptr +
					   sizeof(topo) +
					   slice_length + subslice_length),
			   sseu->eu_mask, eu_length))
		return -EFAULT;

	return total_length;
}