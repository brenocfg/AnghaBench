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
struct nouveau_cli {int /*<<< orphan*/  mutex; struct nouveau_abi16* abi16; } ;
struct nouveau_abi16 {int dummy; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nouveau_abi16 (struct drm_file*) ; 
 struct nouveau_cli* nouveau_cli (struct drm_file*) ; 

struct nouveau_abi16 *
nouveau_abi16_get(struct drm_file *file_priv)
{
	struct nouveau_cli *cli = nouveau_cli(file_priv);
	mutex_lock(&cli->mutex);
	if (nouveau_abi16(file_priv))
		return cli->abi16;
	mutex_unlock(&cli->mutex);
	return NULL;
}