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
struct video_device {int dummy; } ;
struct ipu_csc_scaler_priv {int /*<<< orphan*/  m2m_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ipu_csc_scaler_priv*) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 struct ipu_csc_scaler_priv* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static void ipu_csc_scaler_video_device_release(struct video_device *vdev)
{
	struct ipu_csc_scaler_priv *priv = video_get_drvdata(vdev);

	v4l2_m2m_release(priv->m2m_dev);
	video_device_release(vdev);
	kfree(priv);
}