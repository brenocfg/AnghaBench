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
typedef  int uint32 ;
typedef  int SVGAOverlayFormat ;

/* Variables and functions */
#define  VMWARE_FOURCC_UYVY 130 
#define  VMWARE_FOURCC_YUY2 129 
#define  VMWARE_FOURCC_YV12 128 

__attribute__((used)) static inline bool
VMwareVideoGetAttributes(const SVGAOverlayFormat format,    /* IN */
                         uint32 *width,                     /* IN / OUT */
                         uint32 *height,                    /* IN / OUT */
                         uint32 *size,                      /* OUT */
                         uint32 *pitches,                   /* OUT (optional) */
                         uint32 *offsets)                   /* OUT (optional) */
{
    int tmp;

    *width = (*width + 1) & ~1;

    if (offsets) {
        offsets[0] = 0;
    }

    switch (format) {
    case VMWARE_FOURCC_YV12:
       *height = (*height + 1) & ~1;
       *size = (*width) * (*height);

       if (pitches) {
          pitches[0] = *width;
       }

       if (offsets) {
          offsets[1] = *size;
       }

       tmp = *width >> 1;

       if (pitches) {
          pitches[1] = pitches[2] = tmp;
       }

       tmp *= (*height >> 1);
       *size += tmp;

       if (offsets) {
          offsets[2] = *size;
       }

       *size += tmp;
       break;

    case VMWARE_FOURCC_YUY2:
    case VMWARE_FOURCC_UYVY:
       *size = *width * 2;

       if (pitches) {
          pitches[0] = *size;
       }

       *size *= *height;
       break;

    default:
       return false;
    }

    return true;
}