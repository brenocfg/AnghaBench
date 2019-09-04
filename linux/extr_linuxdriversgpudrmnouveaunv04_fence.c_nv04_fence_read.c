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
struct nv04_nvsw_get_ref_v0 {int /*<<< orphan*/  ref; } ;
struct nouveau_channel {int /*<<< orphan*/  nvsw; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_NVSW_GET_REF ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvif_object_mthd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nv04_nvsw_get_ref_v0*,int) ; 

__attribute__((used)) static u32
nv04_fence_read(struct nouveau_channel *chan)
{
	struct nv04_nvsw_get_ref_v0 args = {};
	WARN_ON(nvif_object_mthd(&chan->nvsw, NV04_NVSW_GET_REF,
				 &args, sizeof(args)));
	return args.ref;
}