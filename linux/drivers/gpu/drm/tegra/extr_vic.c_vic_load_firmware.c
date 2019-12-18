#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * drm; } ;
struct vic {TYPE_3__ falcon; TYPE_2__* config; TYPE_1__ client; } ;
struct TYPE_6__ {int /*<<< orphan*/  firmware; } ;

/* Variables and functions */
 int falcon_load_firmware (TYPE_3__*) ; 
 int falcon_read_firmware (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vic_load_firmware(struct vic *vic)
{
	int err;

	if (vic->falcon.data)
		return 0;

	vic->falcon.data = vic->client.drm;

	err = falcon_read_firmware(&vic->falcon, vic->config->firmware);
	if (err < 0)
		goto cleanup;

	err = falcon_load_firmware(&vic->falcon);
	if (err < 0)
		goto cleanup;

	return 0;

cleanup:
	vic->falcon.data = NULL;
	return err;
}