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
struct nv_device_v0 {unsigned long long device; } ;
struct TYPE_2__ {int /*<<< orphan*/  object; } ;
struct nouveau_cli {struct nouveau_abi16* abi16; TYPE_1__ base; } ;
struct nouveau_abi16 {int /*<<< orphan*/  device; int /*<<< orphan*/  channels; } ;
struct drm_file {int dummy; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NV_DEVICE ; 
 int /*<<< orphan*/  kfree (struct nouveau_abi16*) ; 
 struct nouveau_abi16* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nouveau_cli* nouveau_cli (struct drm_file*) ; 
 scalar_t__ nvif_device_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nv_device_v0*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nouveau_abi16 *
nouveau_abi16(struct drm_file *file_priv)
{
	struct nouveau_cli *cli = nouveau_cli(file_priv);
	if (!cli->abi16) {
		struct nouveau_abi16 *abi16;
		cli->abi16 = abi16 = kzalloc(sizeof(*abi16), GFP_KERNEL);
		if (cli->abi16) {
			struct nv_device_v0 args = {
				.device = ~0ULL,
			};

			INIT_LIST_HEAD(&abi16->channels);

			/* allocate device object targeting client's default
			 * device (ie. the one that belongs to the fd it
			 * opened)
			 */
			if (nvif_device_init(&cli->base.object, 0, NV_DEVICE,
					     &args, sizeof(args),
					     &abi16->device) == 0)
				return cli->abi16;

			kfree(cli->abi16);
			cli->abi16 = NULL;
		}
	}
	return cli->abi16;
}