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
typedef  int v4l2_std_id ;
struct solo_enc_dev {int /*<<< orphan*/  solo_dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int V4L2_STD_625_50 ; 
 int solo_set_video_type (int /*<<< orphan*/ ,int) ; 
 struct solo_enc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int solo_enc_s_std(struct file *file, void *priv, v4l2_std_id std)
{
	struct solo_enc_dev *solo_enc = video_drvdata(file);

	return solo_set_video_type(solo_enc->solo_dev, std & V4L2_STD_625_50);
}