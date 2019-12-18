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
struct TYPE_10__ {int /*<<< orphan*/  device_virt_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  mem_size; } ;
struct TYPE_11__ {int op; TYPE_4__ unmap; TYPE_2__ free; TYPE_1__ alloc; } ;
struct TYPE_9__ {int /*<<< orphan*/  device_virt_addr; int /*<<< orphan*/  handle; } ;
union hl_mem_args {TYPE_5__ in; TYPE_3__ out; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hl_fpriv {struct hl_ctx* ctx; struct hl_device* hdev; } ;
struct hl_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  dram_supports_virtual_memory; int /*<<< orphan*/  mmu_enable; int /*<<< orphan*/  in_reset; } ;
struct hl_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOTTY ; 
#define  HL_MEM_OP_ALLOC 131 
#define  HL_MEM_OP_FREE 130 
#define  HL_MEM_OP_MAP 129 
#define  HL_MEM_OP_UNMAP 128 
 int alloc_device_memory (struct hl_ctx*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,char*) ; 
 int free_device_memory (struct hl_ctx*,int /*<<< orphan*/ ) ; 
 scalar_t__ hl_device_disabled_or_in_reset (struct hl_device*) ; 
 int map_device_va (struct hl_ctx*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int mem_ioctl_no_mmu (struct hl_fpriv*,union hl_mem_args*) ; 
 int /*<<< orphan*/  memset (union hl_mem_args*,int /*<<< orphan*/ ,int) ; 
 int unmap_device_va (struct hl_ctx*,int /*<<< orphan*/ ) ; 

int hl_mem_ioctl(struct hl_fpriv *hpriv, void *data)
{
	union hl_mem_args *args = data;
	struct hl_device *hdev = hpriv->hdev;
	struct hl_ctx *ctx = hpriv->ctx;
	u64 device_addr = 0;
	u32 handle = 0;
	int rc;

	if (hl_device_disabled_or_in_reset(hdev)) {
		dev_warn_ratelimited(hdev->dev,
			"Device is %s. Can't execute MEMORY IOCTL\n",
			atomic_read(&hdev->in_reset) ? "in_reset" : "disabled");
		return -EBUSY;
	}

	if (!hdev->mmu_enable)
		return mem_ioctl_no_mmu(hpriv, args);

	switch (args->in.op) {
	case HL_MEM_OP_ALLOC:
		if (!hdev->dram_supports_virtual_memory) {
			dev_err(hdev->dev, "DRAM alloc is not supported\n");
			rc = -EINVAL;
			goto out;
		}

		if (args->in.alloc.mem_size == 0) {
			dev_err(hdev->dev,
				"alloc size must be larger than 0\n");
			rc = -EINVAL;
			goto out;
		}
		rc = alloc_device_memory(ctx, &args->in, &handle);

		memset(args, 0, sizeof(*args));
		args->out.handle = (__u64) handle;
		break;

	case HL_MEM_OP_FREE:
		rc = free_device_memory(ctx, args->in.free.handle);
		break;

	case HL_MEM_OP_MAP:
		rc = map_device_va(ctx, &args->in, &device_addr);

		memset(args, 0, sizeof(*args));
		args->out.device_virt_addr = device_addr;
		break;

	case HL_MEM_OP_UNMAP:
		rc = unmap_device_va(ctx,
				args->in.unmap.device_virt_addr);
		break;

	default:
		dev_err(hdev->dev, "Unknown opcode for memory IOCTL\n");
		rc = -ENOTTY;
		break;
	}

out:
	return rc;
}