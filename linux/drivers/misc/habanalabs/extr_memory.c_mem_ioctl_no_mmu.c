#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  device_virt_addr; int /*<<< orphan*/  handle; } ;
struct TYPE_9__ {int /*<<< orphan*/  host_virt_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  mem_size; } ;
struct TYPE_11__ {int op; int flags; TYPE_3__ map_host; TYPE_2__ free; TYPE_1__ alloc; } ;
union hl_mem_args {TYPE_4__ out; TYPE_5__ in; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hl_fpriv {struct hl_ctx* ctx; struct hl_device* hdev; } ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
 int HL_MEM_CONTIGUOUS ; 
#define  HL_MEM_OP_ALLOC 131 
#define  HL_MEM_OP_FREE 130 
#define  HL_MEM_OP_MAP 129 
#define  HL_MEM_OP_UNMAP 128 
 int HL_MEM_USERPTR ; 
 int alloc_device_memory (struct hl_ctx*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int free_device_memory (struct hl_ctx*,int /*<<< orphan*/ ) ; 
 int get_paddr_from_handle (struct hl_ctx*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (union hl_mem_args*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mem_ioctl_no_mmu(struct hl_fpriv *hpriv, union hl_mem_args *args)
{
	struct hl_device *hdev = hpriv->hdev;
	struct hl_ctx *ctx = hpriv->ctx;
	u64 device_addr = 0;
	u32 handle = 0;
	int rc;

	switch (args->in.op) {
	case HL_MEM_OP_ALLOC:
		if (args->in.alloc.mem_size == 0) {
			dev_err(hdev->dev,
				"alloc size must be larger than 0\n");
			rc = -EINVAL;
			goto out;
		}

		/* Force contiguous as there are no real MMU
		 * translations to overcome physical memory gaps
		 */
		args->in.flags |= HL_MEM_CONTIGUOUS;
		rc = alloc_device_memory(ctx, &args->in, &handle);

		memset(args, 0, sizeof(*args));
		args->out.handle = (__u64) handle;
		break;

	case HL_MEM_OP_FREE:
		rc = free_device_memory(ctx, args->in.free.handle);
		break;

	case HL_MEM_OP_MAP:
		if (args->in.flags & HL_MEM_USERPTR) {
			device_addr = args->in.map_host.host_virt_addr;
			rc = 0;
		} else {
			rc = get_paddr_from_handle(ctx, &args->in,
					&device_addr);
		}

		memset(args, 0, sizeof(*args));
		args->out.device_virt_addr = device_addr;
		break;

	case HL_MEM_OP_UNMAP:
		rc = 0;
		break;

	default:
		dev_err(hdev->dev, "Unknown opcode for memory IOCTL\n");
		rc = -ENOTTY;
		break;
	}

out:
	return rc;
}