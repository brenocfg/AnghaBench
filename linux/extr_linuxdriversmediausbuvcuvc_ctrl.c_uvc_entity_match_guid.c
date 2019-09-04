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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  guidExtensionCode; } ;
struct uvc_entity {TYPE_1__ extension; } ;

/* Variables and functions */
 int UVC_ENTITY_TYPE (struct uvc_entity const*) ; 
#define  UVC_ITT_CAMERA 131 
#define  UVC_ITT_MEDIA_TRANSPORT_INPUT 130 
#define  UVC_VC_EXTENSION_UNIT 129 
#define  UVC_VC_PROCESSING_UNIT 128 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  uvc_camera_guid ; 
 int /*<<< orphan*/  uvc_media_transport_input_guid ; 
 int /*<<< orphan*/  uvc_processing_guid ; 

__attribute__((used)) static int uvc_entity_match_guid(const struct uvc_entity *entity,
	const u8 guid[16])
{
	switch (UVC_ENTITY_TYPE(entity)) {
	case UVC_ITT_CAMERA:
		return memcmp(uvc_camera_guid, guid, 16) == 0;

	case UVC_ITT_MEDIA_TRANSPORT_INPUT:
		return memcmp(uvc_media_transport_input_guid, guid, 16) == 0;

	case UVC_VC_PROCESSING_UNIT:
		return memcmp(uvc_processing_guid, guid, 16) == 0;

	case UVC_VC_EXTENSION_UNIT:
		return memcmp(entity->extension.guidExtensionCode,
			      guid, 16) == 0;

	default:
		return 0;
	}
}