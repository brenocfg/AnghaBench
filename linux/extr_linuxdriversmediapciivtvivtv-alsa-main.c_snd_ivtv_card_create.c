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
struct v4l2_device {int dummy; } ;
struct snd_ivtv_card {struct snd_card* sc; struct v4l2_device* v4l2_dev; } ;
struct snd_card {int /*<<< orphan*/  private_free; struct snd_ivtv_card* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_ivtv_card* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ivtv_card_private_free ; 

__attribute__((used)) static int snd_ivtv_card_create(struct v4l2_device *v4l2_dev,
				       struct snd_card *sc,
				       struct snd_ivtv_card **itvsc)
{
	*itvsc = kzalloc(sizeof(struct snd_ivtv_card), GFP_KERNEL);
	if (*itvsc == NULL)
		return -ENOMEM;

	(*itvsc)->v4l2_dev = v4l2_dev;
	(*itvsc)->sc = sc;

	sc->private_data = *itvsc;
	sc->private_free = snd_ivtv_card_private_free;

	return 0;
}