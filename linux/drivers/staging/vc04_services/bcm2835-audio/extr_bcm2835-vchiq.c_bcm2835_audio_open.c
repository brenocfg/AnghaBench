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
struct bcm2835_vchi_ctx {int /*<<< orphan*/  vchi_instance; } ;
struct bcm2835_audio_instance {int peer_version; int max_packet; int /*<<< orphan*/  vchi_handle; struct bcm2835_alsa_stream* alsa_stream; int /*<<< orphan*/  dev; int /*<<< orphan*/  vchi_mutex; } ;
struct bcm2835_alsa_stream {struct bcm2835_audio_instance* instance; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct bcm2835_vchi_ctx* vchi_ctx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VC_AUDIO_MSG_TYPE_OPEN ; 
 int /*<<< orphan*/  bcm2835_audio_lock (struct bcm2835_audio_instance*) ; 
 int bcm2835_audio_send_simple (struct bcm2835_audio_instance*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm2835_audio_unlock (struct bcm2835_audio_instance*) ; 
 scalar_t__ force_bulk ; 
 int /*<<< orphan*/  kfree (struct bcm2835_audio_instance*) ; 
 struct bcm2835_audio_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_vchi_audio_deinit (struct bcm2835_audio_instance*) ; 
 int vc_vchi_audio_init (int /*<<< orphan*/ ,struct bcm2835_audio_instance*) ; 
 int /*<<< orphan*/  vchi_get_peer_version (int /*<<< orphan*/ ,int*) ; 

int bcm2835_audio_open(struct bcm2835_alsa_stream *alsa_stream)
{
	struct bcm2835_vchi_ctx *vchi_ctx = alsa_stream->chip->vchi_ctx;
	struct bcm2835_audio_instance *instance;
	int err;

	/* Allocate memory for this instance */
	instance = kzalloc(sizeof(*instance), GFP_KERNEL);
	if (!instance)
		return -ENOMEM;
	mutex_init(&instance->vchi_mutex);
	instance->dev = alsa_stream->chip->dev;
	instance->alsa_stream = alsa_stream;
	alsa_stream->instance = instance;

	err = vc_vchi_audio_init(vchi_ctx->vchi_instance,
				 instance);
	if (err < 0)
		goto free_instance;

	err = bcm2835_audio_send_simple(instance, VC_AUDIO_MSG_TYPE_OPEN,
					false);
	if (err < 0)
		goto deinit;

	bcm2835_audio_lock(instance);
	vchi_get_peer_version(instance->vchi_handle, &instance->peer_version);
	bcm2835_audio_unlock(instance);
	if (instance->peer_version < 2 || force_bulk)
		instance->max_packet = 0; /* bulk transfer */
	else
		instance->max_packet = 4000;

	return 0;

 deinit:
	vc_vchi_audio_deinit(instance);
 free_instance:
	alsa_stream->instance = NULL;
	kfree(instance);
	return err;
}