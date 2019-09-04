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
struct i2c_adapter {int dummy; } ;
struct nvkm_i2c_bus {struct i2c_adapter i2c; } ;
struct nvkm_i2c_aux {struct i2c_adapter i2c; } ;
struct nvkm_i2c {int dummy; } ;
struct nouveau_encoder {struct nvkm_i2c_aux* aux; struct i2c_adapter* i2c; struct dcb_output* dcb; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct nouveau_drm {TYPE_1__ client; } ;
struct drm_encoder {scalar_t__ possible_clones; int /*<<< orphan*/  possible_crtcs; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;
struct dcb_output {int type; int /*<<< orphan*/  hashm; int /*<<< orphan*/  hasht; int /*<<< orphan*/  heads; int /*<<< orphan*/  extdev; } ;

/* Variables and functions */
#define  DCB_OUTPUT_DP 129 
#define  DCB_OUTPUT_TMDS 128 
 int DRM_MODE_ENCODER_TMDS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVKM_I2C_AUX_EXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVKM_I2C_BUS_EXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (int /*<<< orphan*/ ,struct drm_encoder*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nouveau_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_pior_func ; 
 int /*<<< orphan*/  nv50_pior_help ; 
 struct nvkm_i2c_aux* nvkm_i2c_aux_find (struct nvkm_i2c*,int /*<<< orphan*/ ) ; 
 struct nvkm_i2c_bus* nvkm_i2c_bus_find (struct nvkm_i2c*,int /*<<< orphan*/ ) ; 
 struct nvkm_i2c* nvxx_i2c (int /*<<< orphan*/ *) ; 
 struct drm_encoder* to_drm_encoder (struct nouveau_encoder*) ; 

__attribute__((used)) static int
nv50_pior_create(struct drm_connector *connector, struct dcb_output *dcbe)
{
	struct nouveau_drm *drm = nouveau_drm(connector->dev);
	struct nvkm_i2c *i2c = nvxx_i2c(&drm->client.device);
	struct nvkm_i2c_bus *bus = NULL;
	struct nvkm_i2c_aux *aux = NULL;
	struct i2c_adapter *ddc;
	struct nouveau_encoder *nv_encoder;
	struct drm_encoder *encoder;
	int type;

	switch (dcbe->type) {
	case DCB_OUTPUT_TMDS:
		bus  = nvkm_i2c_bus_find(i2c, NVKM_I2C_BUS_EXT(dcbe->extdev));
		ddc  = bus ? &bus->i2c : NULL;
		type = DRM_MODE_ENCODER_TMDS;
		break;
	case DCB_OUTPUT_DP:
		aux  = nvkm_i2c_aux_find(i2c, NVKM_I2C_AUX_EXT(dcbe->extdev));
		ddc  = aux ? &aux->i2c : NULL;
		type = DRM_MODE_ENCODER_TMDS;
		break;
	default:
		return -ENODEV;
	}

	nv_encoder = kzalloc(sizeof(*nv_encoder), GFP_KERNEL);
	if (!nv_encoder)
		return -ENOMEM;
	nv_encoder->dcb = dcbe;
	nv_encoder->i2c = ddc;
	nv_encoder->aux = aux;

	encoder = to_drm_encoder(nv_encoder);
	encoder->possible_crtcs = dcbe->heads;
	encoder->possible_clones = 0;
	drm_encoder_init(connector->dev, encoder, &nv50_pior_func, type,
			 "pior-%04x-%04x", dcbe->hasht, dcbe->hashm);
	drm_encoder_helper_add(encoder, &nv50_pior_help);

	drm_connector_attach_encoder(connector, encoder);
	return 0;
}