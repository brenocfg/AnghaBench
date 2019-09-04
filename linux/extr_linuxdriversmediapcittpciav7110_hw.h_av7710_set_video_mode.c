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
struct av7110 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMTYPE_ENCODER ; 
 int /*<<< orphan*/  SetVidMode ; 
 int av7110_fw_cmd (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int av7710_set_video_mode(struct av7110 *av7110, int mode)
{
	return av7110_fw_cmd(av7110, COMTYPE_ENCODER, SetVidMode, 1, mode);
}