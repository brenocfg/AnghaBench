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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  eld; } ;
struct sii902x {int /*<<< orphan*/  mutex; TYPE_1__ connector; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sii902x* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sii902x_audio_get_eld(struct device *dev, void *data,
				 uint8_t *buf, size_t len)
{
	struct sii902x *sii902x = dev_get_drvdata(dev);

	mutex_lock(&sii902x->mutex);

	memcpy(buf, sii902x->connector.eld,
	       min(sizeof(sii902x->connector.eld), len));

	mutex_unlock(&sii902x->mutex);

	return 0;
}