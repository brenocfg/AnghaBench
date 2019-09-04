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
struct inode {struct drm_crtc* i_private; } ;
struct file {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crc_control_show ; 
 int single_open (struct file*,int /*<<< orphan*/ ,struct drm_crtc*) ; 

__attribute__((used)) static int crc_control_open(struct inode *inode, struct file *file)
{
	struct drm_crtc *crtc = inode->i_private;

	return single_open(file, crc_control_show, crtc);
}